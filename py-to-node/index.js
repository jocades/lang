const { spawn } = require("child_process")

const obj = { name: "Jordi", age: 10 }

const script = spawn("python", ["return.py", JSON.stringify(obj)])

script.stdout.on("data", (data) => {
  console.log(`stdout: ${data}`)
  const last = data.toString().split("\n")[2]
  console.log(last.slice(2))

  console.log(typeof data.toString())
})

script.stderr.on("data", (data) => {
  console.log(`stderr: ${data}`)
})

script.on("close", (code) => {
  console.log(`child process exited with code ${code}`)
})
