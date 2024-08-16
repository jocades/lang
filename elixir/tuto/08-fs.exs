{:ok, file} = File.open("test.txt", [:write])

IO.binwrite(file, "world")
File.close(file)

{:ok, contents} = File.read("test.txt")

IO.puts(contents)
