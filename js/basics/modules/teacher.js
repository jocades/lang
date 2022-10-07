import { Person } from "./person";

export function promote() {}
export class Teacher extends Person {
    constructor(name, degree) {
        // we have to call the parent constructor and pass in the name argument
        super(name);
        this.degree = degree;
    }
    
    teach() {
        console.log('teach');
    }
}