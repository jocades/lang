# processes

pid = spawn(fn -> 1 + 2 end)
IO.puts(Process.alive?(pid))

Process.alive?(self())

# sending and receiving messages

send self(), {:hello, "world"}

receive do
  {:hello, msg} -> msg
  {:world, _msg} -> "won't match"
end

receive do
  {:hello, msg} -> msg
after
  1_000 -> "nothing after 1s"
end

# all together

parent = self()

spawn(fn -> send(parent, {:hello, self()}) end)

receive do
  {:hello, pid} -> IO.puts "Got hello from #{inspect pid}"
end

# tip: flus() prints all the messages in the mailbox
# send(self(), :hello)
# :hello
# flush()
# :hello
# :ok

