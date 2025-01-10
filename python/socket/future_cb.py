from collections import deque
from dataclasses import dataclass
from enum import Enum
from typing import Any, Callable, Generator, Deque


class State(Enum):
    PENDING = "PENDING"
    COMPLETED = "COMPLETED"
    FAILED = "FAILED"


@dataclass
class Future:
    """Reperesents an asynchronous computation that may or may not have completed"""

    # _state: State = State.PENDING
    # _result: Any = None
    # _callbacks: list[Callable] = []

    def __init__(self):
        self._state: State = State.PENDING
        self._callbacks: list[Callable] = []
        self._result: Any = None

    def set_result(self, result):
        self._result = result
        self._state = State.COMPLETED
        for cb in self._callbacks:
            cb(self)
        self._callbacks = []

    def add_done_callback(self, fn: Callable[["Future"], None]):
        if self._state == State.COMPLETED:
            fn(self)
        else:
            self._callbacks.append(fn)

    def result(self):
        if self._state != State.COMPLETED:
            raise RuntimeError("Result not ready")
        return self._result


class Task:
    """Wraps a coroutine and manages its execution"""

    def __init__(self, coro: Generator):
        self.coro = coro
        self.future = Future()
        self._step()

    def _step(self, value=None):
        """Advances the coroutine one step"""
        try:
            if value is None:
                # Initial step
                fut = next(self.coro)
            else:
                # Subsequent steps with the result from the previous future
                fut = self.coro.send(value)

            # Register the callback when the future completes
            fut.add_done_callback(self._wakeup)
        except StopIteration as e:
            # Coroutine has completed
            self.future.set_result(e.value if e.value is not None else None)

    def _wakeup(self, future: Future):
        """Callback that runs when the future completes"""
        self._step(future.result())


class EventLoop:
    """A simple event loop that manages the execution of tasks"""

    def __init__(self):
        self.ready: Deque[Task] = deque()
        self.stopping = False

    def create_task(self, coro: Generator[Any, Any, Any]):
        """Creates a new task from a coroutine"""
        task = Task(coro)
        return task

    def run_until_complete(self, fut: Future):
        """Runs the event loop until the given future completes"""
        fut.add_done_callback(lambda _: self.stop())
        self.run_forever()
        return fut.result()

    def stop(self):
        """Stops the event loop"""
        self.stopping = True

    def run_forever(self):
        """Runs the event loop indefinitely"""
        self.stopping = False
        while not self.stopping:
            # Process any ready tasks
            while self.ready:
                task = self.ready.popleft()
                task._step()

                # In a real event loop, we would poll for I/O here
                # For now we will just break if there is nothing to do
                if not self.ready:
                    break


# Global event loop
_loop = EventLoop()


def get_event_loop() -> EventLoop:
    """Returns the global event loop instance"""
    return _loop
