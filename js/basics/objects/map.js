const num = 3 

const arr = [1,2,3,4,5]

let count = 0

arr.map((a, index) => {
  
  count++
  console.log(count, index)
  
})

console.log(count)
