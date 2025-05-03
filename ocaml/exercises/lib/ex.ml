(* Tail of a List *)
let rec last = function
  | [] -> None
  | [ x ] -> Some x
  | _ :: t -> last t
;;

(* Last two elements of a List *)
let rec last_two = function
  | [] -> None
  | [ x; y ] -> Some (x, y)
  | _ :: t -> last_two t
;;

(* N'th element of a List *)
let rec at k = function
  | [] -> None
  | h :: t -> if k = 0 then Some h else at (k - 1) t
;;

(* Length of a List *)
let rec length = function
  | [] -> 0
  | _ :: t -> 1 + length t
;;

(*
   [1; 2; 3]
   => 1 + (length [2; 3])
   => 1 + (1 + (length [3]))
   => 1 + (1 + (1 + length []))
   => 1 + (1 + (1 + 0))
   => 1 + (1 + 1)
   => 1 + 2
   => 3

   _not_ tail recursive since the function has to wait for the next call to
   finish to add 1 to the result therefore a new stack frame has to be created
   for each recursive call:
   -----------------------------
   | ... | 1+x | ret | x | ret |
   -----------------------------
   |_ 2 _|____ 1 ____|___ 0 ___|

   if we make it a tail call recursive function the argument can be mutated
   in place using the _same_ stack frame:
   -----------    -----------
   | x | ret | -> | 1 | ret | -> ...
   -----------    -----------
   |___ 0 ___|    |___ 0 ___|
*)

let length_tail list =
  let rec aux acc = function
    | [] -> 0
    | _ :: t -> aux (acc + 1) t
  in
  aux 0 list
;;

(* Reverse a List *)
let rev list =
  let rec rev' acc = function
    | [] -> acc
    | h :: t -> rev' (h :: acc) t
  in
  rev' [] list
;;

(* Palindrome *)
let is_palindrome list = list = rev list

(* Flatten a list *)
type 'a node =
  | One of 'a
  | Many of 'a node list

let flatten list =
  let rec flatten' acc = function
    (*
       | [] -> List.rev acc
       | h :: t ->
         (match h with
         | One x -> flatten' (x :: acc) t
         | Many l -> flatten' acc l)
    *)
    | [] -> acc
    | One x :: t -> flatten' (x :: acc) t
    | Many l :: t -> flatten' (flatten' acc l) t
  in
  List.rev (flatten' [] list)
;;

(* Eliminate consecutive duplicates of a List *)
let rec compress = function
  | a :: (b :: _ as t) -> if a = b then compress t else a :: compress t
  | smaller -> smaller
;;

(* Pack consecutive duplicates into sublists *)
let pack list =
  let rec pack' current acc = function
    | [] -> [] (* can only be reached if the original list is empty *)
    | [ x ] -> (x :: current) :: acc
    | a :: (b :: _ as t) ->
      if a = b then pack' (a :: current) acc t else pack' [] ((a :: current) :: acc) t
  in
  List.rev (pack' [] [] list)
;;

(* Run-length encoding *)
let encode list =
  let rec encode' count acc = function
    | [] -> [] (* can only be reached if the original list is empty *)
    | [ x ] -> (count + 1, x) :: acc
    | a :: (b :: _ as t) ->
      if a = b then encode' (count + 1) acc t else encode' 0 ((count + 1, a) :: acc) t
  in
  List.rev (encode' 0 [] list)
;;

(* Modified run-length encoding *)
type 'a rle =
  | One of 'a
  | Many of int * 'a

let mencode list =
  let create_rle n x = if n = 1 then One x else Many (n, x) in
  let rec aux count acc = function
    | [] -> []
    | [ x ] -> create_rle (count + 1) x :: acc
    | a :: (b :: _ as t) ->
      if a = b then aux (count + 1) acc t else aux 0 (create_rle (count + 1) a :: acc) t
  in
  aux 0 [] list |> List.rev
;;

(* Decode a modified run-length encoded list *)
let mdecode list =
  let rec many acc n x = if n = 0 then acc else many (x :: acc) (n - 1) x in
  let rec aux acc = function
    | [] -> acc
    | One x :: t -> aux (x :: acc) t
    | Many (n, x) :: t -> aux (many acc n x) t
  in
  aux [] (List.rev list)
;;

(* Duplicate the elements of a list *)
let rec duplicate = function
  | [] -> []
  | h :: t -> h :: h :: duplicate t
;;

(* Replicate the elements of a list a given number of times *)
let replicate list k =
  let rec prepend n acc x = if n = 0 then acc else prepend (n - 1) (x :: acc) x in
  let rec aux acc = function
    | [] -> acc
    | h :: t -> aux (prepend k acc h) t
  in
  (* This could also be written as:
    List.fold_left (prepend n) [] (List.rev list)
  *)
  aux [] (List.rev list)
;;
