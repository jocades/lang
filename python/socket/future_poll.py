from collections import deque
from dataclasses import dataclass
from enum import Enum
from typing import Any, Callable, Generator, Deque, Optional


class Poll(Enum):
    READY = "READY"
    PENDING = "PENDING"


class PollResult[T]:
    def __init__(
        self,
        state: Poll,
        value: Optional[T] = None,
        error: Optional[Exception] = None,
    ):
        self.state = state
        self.value = value
        self.error = error

    @classmethod
    def ready(cls, value: T) -> "PollResult[T]":
        return cls(Poll.READY, value=value)

    @classmethod
    def pending(cls) -> "PollResult[T]":
        return cls(Poll.PENDING)

    @classmethod
    def error(cls, error) -> "PollResult[T]":
        return cls(Poll.READY, error=error)


class Future[T]:
    def poll(self) -> PollResult[T]:
        raise NotImplementedError()


class ReadyFuture[T](Future[T]):
    def __init__(self, coro: Generator):
        self.coro = coro
        self.current_future: Optional[Future] = None
        self._complete = False
        self._result: Optional[T] = None
        self._error: Optional[Exception] = None

        # Initial polling to start the coroutine
        try:
            self.current_future = next(self.coro)
        except StopIteration as e:
            self._complete = True
            self._result = e.value
        except Exception as e:
            self._complete = True
            self._error = e

    def poll(self) -> PollResult[T]:
        # If task is complete return the result or error
        if self._complete:
            if self._error:
                return PollResult.error(self._error)
            return PollResult.ready(self._result)

        # Check if we have a current future to poll
        if self.current_future:
            poll_result = self.current_future.poll()

            if poll_result == Poll.PENDING:
                return PollResult.pending()

            try:
                if poll_result.error:
                    self.current_future = self.coro.throw(poll_result.error)
                else:
                    self.current_future = self.coro.send(poll_result.value)
