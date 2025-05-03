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
let pack list = ()

(* Run-length encoding *)
let encode list = ()
