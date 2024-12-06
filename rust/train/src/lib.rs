fn magic_triangle_solutions(puzzle: &[u8; 9]) -> Vec<[u8; 9]> {
    let r = &puzzle[..4];
    let b = &puzzle[3..7];
    let l = [&puzzle[6..], &puzzle[..1]].concat();

    puzzle.windows(3);

    println!("{r:?} {b:?} {l:?}");

    if r.iter().any(|&n| n == 0) {}

    let mut i = 0;
    loop {
        let n = puzzle[i];
        println!("index = {i} value = {n}");
        i = (i + 1) % puzzle.len();
    }

    todo!();
}

#[cfg(test)]
mod sample_tests {
    use super::magic_triangle_solutions;

    #[test]
    fn zero_solutions() {
        do_test(&[1, 2, 3, 4, 0, 0, 0, 0, 0], &mut []);
    }

    #[test]
    fn single_solution() {
        do_test(
            &[9, 4, 0, 0, 2, 0, 0, 5, 0],
            &mut [[9, 4, 3, 7, 2, 6, 8, 5, 1]],
        );
    }

    #[test]
    fn multiple_solutions() {
        do_test(
            &[0, 4, 0, 0, 2, 0, 0, 5, 0],
            &mut [
                [6, 4, 8, 3, 2, 7, 9, 5, 1],
                [8, 4, 6, 3, 2, 9, 7, 5, 1],
                [9, 4, 3, 7, 2, 6, 8, 5, 1],
            ],
        );
    }

    fn do_test(puzzle: &[u8; 9], expected: &mut [[u8; 9]]) {
        let mut actual = magic_triangle_solutions(puzzle);
        actual.sort_unstable();
        expected.sort_unstable();
        if actual.len() != expected.len() {
            panic!("Wrong number of solutions\nInput: {puzzle:?}\nActual:   {} solutions\nExpected: {} solutions\n",
                    actual.len(), expected.len()
            );
        }
        for (i, (a, e)) in actual.iter().zip(expected.iter()).enumerate() {
            if *a != *e {
                panic!("Wrong solution\nThe {i}th solution in your (sorted) result didn't match the expected solution\n\
                        Input:    {puzzle:?}\n\nActual:   {a:?}\nExpected: {e:?}\n"
                );
            }
        }
    }
}
