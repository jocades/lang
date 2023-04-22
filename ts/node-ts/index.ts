import express from "express"
const app = express()

import listRouter from "./router"

app.get("/", (req, res) => {
  res.send({ message: "Hello" })
})

app.use("/list", listRouter)

app.listen(8000, () => console.log("Server started..."))
