type filesystem =
  | File of string
  | Directory of filesystem list

let readdir_noex dirh =
  try Some (Unix.readdir dirh) with
  | End_of_file -> None
;;

let rec string_of_filesystem fs =
  match fs with
  | File name -> name ^ "\n"
  | Directory fs_list ->
    fs_list
    |> List.map string_of_filesystem
    |> String.concat "" (* String.concat "" (List.map string_of_filesystem fs_list) *)
;;

let rec read_directory path =
  let dirh = Unix.opendir path in
  let rec loop () =
    let filename = readdir_noex dirh in
    match filename with
    | None -> []
    | Some "." -> loop ()
    | Some ".." -> loop ()
    | Some filename ->
      let pathname = path ^ "/" ^ filename in
      let stat = Unix.lstat pathname in
      let this =
        if stat.st_kind = S_DIR then read_directory pathname else File pathname
      in
      this :: loop ()
  in
  Directory (loop ())
;;

(* let run path =
  let fs = read_directory path in
  print_endline (string_of_filesystem fs)
;; *)

let run path = path |> read_directory |> string_of_filesystem |> print_endline
