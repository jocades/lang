local loop = {
  tasks = {},
  timers = {},
  time = 0,
}

local function spawn(f)
  local task = { id = #loop.tasks, f = coroutine.create(f) }
  table.insert(loop.tasks, task)
end

local function counter(id, from, to)
  return function()
    for i = from, to do
      print(id .. ": " .. i)
      coroutine.yield()
    end
  end
end

spawn(counter("t0", 1, 2))
spawn(counter("t1", 1, 4))

local function run()
  while #loop.tasks ~= 0 do
    loop.time = loop.time + os.clock()

    for i, task in ipairs(loop.tasks) do
      print("resume t" .. task.id)
      if not coroutine.resume(task.f) then
        print("remove t" .. task.id)
        table.remove(loop.tasks, i)
      end
    end
  end
end

run()

-- local t1 = coroutine.create(counter("t1", 2))
-- local t2 = coroutine.create(counter("t2", 2))
--
-- coroutine.resume(t1)
-- coroutine.resume(t2)
-- coroutine.resume(t1)
-- coroutine.resume(t2)
-- coroutine.resume(t1)
-- coroutine.resume(t2)
-- coroutine.resume(t1)
-- coroutine.resume(t2)
-- coroutine.resume(t1)
-- coroutine.resume(t2)
