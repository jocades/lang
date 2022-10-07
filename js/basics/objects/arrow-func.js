const square = function(number) {
    return number * number;
}

// same as
const squareArrow = (number) => number * number;

console.log(square(5));
console.log(squareArrow(5));

// case scneario
const jobs = [
    { id: 1, isActive: true },
    { id: 1, isActive: true },
    { id: 1, isActive: false },
];

const activeJobs = jobs.filter(function(job) { return job.isActive; })

const activeJobsArrow = jobs.filter(job => job.isActive);

