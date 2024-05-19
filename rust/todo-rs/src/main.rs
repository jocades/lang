use ncurses::*;
use std::process;

struct Terminal;

impl Terminal {
    fn new() -> Self {
        initscr();
        noecho();
        curs_set(CURSOR_VISIBILITY::CURSOR_INVISIBLE);
        Terminal
    }

    fn getsize(&self) -> (i32, i32) {
        let mut w = 0;
        let mut h = 0;
        getmaxyx(stdscr(), &mut h, &mut w);
        (w, h)
    }

    fn getcenter(&self) -> (i32, i32) {
        let (w, h) = self.getsize();
        (w / 2, h / 2)
    }
}

struct Ui {
    current: i32,
    pl: i32,
}

impl Ui {
    fn new(current: i32, pl: i32) -> Self {
        Ui { current, pl }
    }

    fn layout(&self) {
        let (_, h) = Terminal.getsize();
        mv(0, self.pl as i32);
        vline('|' as chtype, h);
    }

    fn list_element(&self, i: usize, todo: &str) {
        mv(i as i32, 0);

        // if i > 10 add a 0 to the left
        let mut text = format!(
            "  {} | {todo}",
            if i < 10 {
                format!("0{i}")
            } else {
                i.to_string()
            },
        );
        text.push_str(" ".repeat(self.pl as usize - text.len()).as_str());

        if i == self.current as usize {
            attron(A_REVERSE());
            addstr(&text);
            attroff(A_REVERSE());
        } else {
            addstr(&text);
        }
    }
}

fn main() {
    let term = Terminal::new();
    let pl = 20; // padding left for the list

    let mut todos = (0..20)
        .map(|i| format!("todo {}", i))
        .collect::<Vec<String>>();

    let mut selected = String::new();

    let mut ui = Ui::new(0, pl);

    loop {
        ui.layout();
        let (w, h) = term.getsize();

        for (i, todo) in todos.iter().enumerate() {
            if i == h as usize {
                break;
            }
            ui.list_element(i, todo);
        }

        match getch() as u8 as char {
            'q' => {
                endwin();
                process::exit(0);
            }
            // DOWN
            'j' => {
                if ui.current < todos.len() as i32 - 1 {
                    ui.current += 1;
                }
            }
            // UP
            'k' => {
                if ui.current > 0 {
                    ui.current -= 1;
                }
            }
            // ENTER
            '\n' => {
                let (x, y) = term.getcenter();
                // clear the prev item off the screen
                mv(y, ui.pl + x - (selected.len() / 2) as i32);
                addstr(&" ".repeat(selected.len()));

                selected = todos[ui.current as usize].to_string();
                mv(y, ui.pl + x - (selected.len() / 2) as i32);
                addstr(&selected);
            }
            'f' => {
                // takw user input
                let (x, y) = term.getcenter();
                mv(y, ui.pl + x - (selected.len() / 2) as i32);
                addstr(&" ".repeat(selected.len()));

                mv(y, ui.pl + x - 5);
                addstr("new todo");
                refresh();

                let mut input = String::new();

                loop {
                    match getch() as u8 as char {
                        // ENTER
                        '\n' => {
                            todos.push(input);
                            break;
                        }
                        // BACKSPACE
                        '\u{7f}' => {
                            input.pop();
                            mv(y, ui.pl + x - 5);
                            addstr("new todo");
                            mv(y + 1, ui.pl + x - (input.len() / 2) as i32);
                            addstr(&input);
                        }
                        // any other char
                        c => {
                            input.push(c);
                            mv(y + 1, ui.pl + x - (input.len() / 2) as i32);
                            addstr(&input);
                        }
                    }
                }

                // ui.current = todos.len() as i32 - 1;
            }
            _ => (),
        }
    }
}
