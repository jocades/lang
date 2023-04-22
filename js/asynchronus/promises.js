// Promise: Object that holds the eventual result of an asynchronous operation
// It can be in one of three states:
// - Pending: initial state, neither fulfilled nor rejected
// - Fulfilled: operation completed successfully
// - Rejected: operation failed

const p = new Promise((resolve, reject) => {
  // Kick off some async work
  // ...
  setTimeout(() => {
    // resolve(1) // pending => fulfilled
    reject(new Error('defined error')) // pending => rejected
  }, 2000)
})

p.then((result) => console.log('Result', result)).catch((err) =>
  console.log('Error', err.message)
)

// Promise-based approach
function getUser(id) {
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      console.log('Reading a user from a database...')
      resolve({ id: id, name: 'Jordi' })
    }, 2000)
  })
}

function getUserExtra(id) {
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      console.log('Calling another server API...')
      resolve(['Juan', 'Pep', 'Maria'])
    }, 2000)
  })
}

console.log('Before')

getUser(1)
  .then((user) => getUserExtra(user.name))
  .then((extra) => console.log(extra))
  .catch((err) => console.log(err.message))

console.log('After')

// consuming promises with async and await
// we need to use a function that is marked as async

async function displayUser() {
  try {
    const user = await getUser(1)
    const extra = await getUserExtra(user.name)
    console.log(extra)
  } catch (err) {
    console.log(err.message)
  }
}

// when an async function is called, it returns a promise
// when in hits the await keyword, it will pause the execution of the function
// and wait for the promise to be resolved
// when the promise is resolved, the value will be stored in the variable
// and the execution of the function will continue
// meanwhile, the thread is free to execute other code

displayUser()
