// Create an already resolved promise for testing purposes
const resolvedP = Promise.resolve({ id: 1 })
resolvedP.then((result) => console.log(result))

// Create an already rejected promise for testing purposes
const rejectedP = Promise.reject(new Error('reason for rejection')) // use error object to get the stack trace
rejectedP.catch((err) => console.log(err.message))

// Run promises in parallel
const p1 = new Promise((resolve) => {
  setTimeout(() => {
    console.log('Async operation 1')
    resolve(1)
  }, 2000)
})

const p2 = new Promise((resolve) => {
  setTimeout(() => {
    console.log('Async operation 2')
    resolve(2)
  }, 2000)
})

// new promise that will be resolved when all the promises in the array are resolved
// if one of the promises is rejected, the new promise will be rejected
// returns an array with the result of each promise
Promise.all([p1, p2]).then((result) => console.log(result))
