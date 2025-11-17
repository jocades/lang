const std = @import("std");
const print = std.debug.print;

const Node = struct {
    value: i32,
    next: [*]Node,
};

pub fn main() void {
    var head = Node{ .value = 1, .next = null };
    for (2..5) |i| {
        const cur = head;
        cur.next = Node{ .value = i, .next = head };
        head = cur;
    }

    while (head.next != null) {
        print("\n", .{});
    }
}
