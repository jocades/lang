// In node, when we are using net or disk access, we are dealing with asynchronous code

// console.log('Before') // this will block the execution of the code
// const user = getUser(1) // -> undefined, because we are not waiting for the result
// console.log('After')

function getUser(id) {
  // this just schedules a task, it doesnt wait, block or pause the execution of the code
  setTimeout(() => {
    console.log('Reading a user from a database...')
    return { id: id, name: 'Jordi' }
  }, 2000)
}

// Dealing with asynchronous code:

// Callbacks: function passed as an argument that will be called when the asynchronous operation is completed
console.log('Before')

// this can lead to callback hell
getUserCallback(1, (user) => {
  getUserExtra(user.name, (extra) => {
    console.log(extra)
  })
})

console.log('After')

function getUserCallback(id, callback) {
  setTimeout(() => {
    console.log('Reading a user from a database...')
    callback({ id: id, name: 'Jordi' })
  }, 2000)
}

function getUserExtra(id, callback) {
  setTimeout(() => {
    console.log('Calling another server API...')
    callback(['Juan', 'Pep', 'Maria'])
  }, 2000)
}

// if we want to make a named function, we can do it like this:
// no need to execute the function, just pass it as a reference and it will receive the result as an argument
getUserCallback(1, getExtra)

function getExtra(user) {
  getUserExtra(user.name, displayExtra)
}

function displayExtra(extra) {
  console.log(extra)
}
