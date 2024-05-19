import express from 'express'
const router = express.Router()

router.get('/', (req, res) => {
  res.send('List')
})

// Dto = dat transfer object
interface CreateTaskDto {
  title: string
}

router.post('/', (req, res) => {
  const { title } = req.body as CreateTaskDto
  res.send({ msg: title })
})

export default router
