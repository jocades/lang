// INTERFACE: to define the structure of an object

// abstract class Calendar {
//   constructor(public name: string) {}

//   abstract addEvent(): void
//   abstract removeEvent(): void
// }

interface Calendar {
  name: string
  addEvent(): void
  removeEvent(): void
}

interface GoogleCalendar extends Calendar {
  sync(): void
}

class GCalendar implements Calendar {
  constructor(public name: string) {}
  addEvent(): void {}
  removeEvent(): void {}
}
