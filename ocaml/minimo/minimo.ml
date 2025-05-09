let file = "example.dat"
let message = "Hello!"

let () =
  (* Write message to file *)
  let oc = open_out file in
  (* create or truncate file, return channel *)
  Printf.fprintf oc "%s\n" message;
  (* write something *)
  close_out oc;

  (* flush and close the channel *)

  (* Read file and display first line *)
  let ic = open_in file in
  try
    let line = input_line ic in
    (* read line, discard \n *)
    print_endline line;
    (* write the result to stdout *)
    flush stdout;
    (* write on the underlying devine now *)
    close_in ic
    (* close the input channel *)
  with e ->
    (* some unexpected excpetion occurs *)
    close_in_noerr ic;
    (* emergency closing *)
    raise e
