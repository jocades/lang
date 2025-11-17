const std = @import("std");
const print = std.debug.print;

fn add(a: i32, b: i32) i32 {
    return a + b;
}

const User = struct {
    name: []u8,
    age: u32,

    fn create(name: []u8) User {
        return User{ .name = name, .age = 10 };
    }

    fn greet(self: @This()) void {
        print("I'm {s} and I'm {d} years old.\n", .{ self.name, self.age });
    }
};

const VM = struct {
    stack: [5]i32 = undefined,

    fn create() @This() {
        return VM{};
    }
};

pub fn main() void {
    print("Hello {s}\n", .{"world"});
    print("{d}\n", .{add(2, 3)});

    // const name: *[]u8 = "John";
    var name = [_]u8{ 'F', 'o', 'o' };
    const user = User.create(&name);
    user.greet();

    var vm = VM.create();
    vm.stack[0] = 1;
    var sp: [*]i32 = &vm.stack;
    sp += 1;
    sp[0] = 2;

    for (vm.stack, 0..) |n, i| {
        print("{d}: {d}\n", .{ i, n });
    }
}
