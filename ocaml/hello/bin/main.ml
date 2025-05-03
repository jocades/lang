let exp1 = Sexplib.Sexp.of_string "(This (is an) (s expression))"
let () = Printf.printf "%s\n" (Sexplib.Sexp.to_string exp1)
let () = print_endline Hello.En.(string_of_string_list v)

let what f x =
  print_endline (string_of_int x);
  f x
;;

let () = what (fun x -> x * x) 2 |> string_of_int |> print_endline
let say_hi ~name = print_endline ("Hi " ^ name ^ "!")

let () =
  say_hi ~name:"Bob";
  say_hi ~name:"bob"
;;
