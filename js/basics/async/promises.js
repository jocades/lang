function requestHandler(req, res) {
  user
    .findById(req.userId)
    .then(function (user) {
      return Tasks.findById(user.tasksId)
    })
    // el return del primer .then seria el argumento del siguiente
    .then(function (tasks) {
      tasks.completed = true
      return tasks.save()
    })
    .then(function () {
      res.send("Taks completed")
    })
    .catch(function (errors) {
      res.send(errors)
    })
}
