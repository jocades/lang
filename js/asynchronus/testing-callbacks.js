const getUser = (id, callback) => {
  setTimeout(() => {
    if (!id) return callback(new Error('No user id'))
    callback(undefined, { id: id, name: 'Jordi' })
  }, 2000)
}

getUser(1, (err, user) => {
  if (err) return console.log(err)
  console.log(user)
})

getUser(null, (err, user) => {
  if (err) return console.log(err)
  console.log(user)
})
