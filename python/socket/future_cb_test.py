from future_cb import Future, get_event_loop


def async_op() -> Future:
    fut = Future()
    fut.set_result("Op completed!")
    return fut


def coroutine():
    result = yield async_op()
    print(f"Got result: {result}")
    return "All done"


def first():
    name = "jordi"
    return name


def wtf():
    name = yield first()
    print(name)
    return "got name"
    # yield "one"
    # yield "two"


def main():
    x = wtf()
    print(next(x))
    print(next(x))


if __name__ == "__main__":
    main()
    # loop = get_event_loop()
    # fut = loop.create_task(coroutine())
    # result = loop.run_until_complete(fut.future)
    # print(f"Final result: {result}")
