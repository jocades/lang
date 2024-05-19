import curses


def main(stdscr: curses.window):
    stdscr.clear()
    curses.use_default_colors()

    h, w = stdscr.getmaxyx()
    print(h, w)

    q = False
    todos = ['todo1', 'todo2', 'todo3']
    current = 0

    while not q:
        for i, todo in enumerate(todos):
            x = 0
            y = i
            if i == current:
                stdscr.addstr(y, x, todo, curses.A_REVERSE)
            else:
                stdscr.addstr(y, x, todo)

        stdscr.refresh()

        key = stdscr.getch()

        if key == ord('q'):
            q = True
        elif key == ord('j'):
            if current < len(todos) - 1:
                current += 1
        elif key == ord('k'):
            if current > 0:
                current -= 1
        elif key == curses.KEY_ENTER or key in [10, 13]:
            stdscr.addstr(w // 2, 0, 'You pressed enter!')
            stdscr.refresh()
        else:
            pass


if __name__ == '__main__':
    curses.wrapper(main)
