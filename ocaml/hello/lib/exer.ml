let rec last = function
  | [] -> None
  | [ x ] -> Some x
  | _ :: t -> last t
;;

let rec last_two = function
  | [] -> None
  | [ x; y ] -> Some (x, y)
  | _ :: t -> last_two t
;;

let rec at n = function
  | [] -> None
  | h :: t -> if n = 0 then Some h else at (n - 1) t
;;

let rec length = function
  | [] -> 0
  | _ :: t -> 1 + length t
;;

let len list =
  let rec aux n = function
    | [] -> 0
    | _ :: t -> aux (n + 1) t
  in
  aux 0 list
;;

let rev list =
  let rec aux acc = function
    | [] -> acc
    | h :: t -> aux (h :: acc) t
  in
  aux [] list
;;

let is_palindrome list = list = rev list

let rec duplicate = function
  | [] -> []
  | h :: t -> h :: h :: duplicate t
;;

let split list n =
  let rec aux i acc = function
    | [] -> List.rev acc, []
    | h :: t as l -> if i = 0 then List.rev acc, l else aux (i - 1) (h :: acc) t
  in
  aux n [] list
;;

let rec remove_at n = function
  | [] -> []
  | h :: t -> if n = 0 then t else h :: remove_at (n - 1) t
;;

let rec insert_at x n = function
  | [] -> [ x ]
  | h :: t as l -> if n = 0 then x :: l else h :: insert_at x (n - 1) t
;;

(* let rec range lo hi = if lo > hi then [] else lo :: range (lo + 1) hi *)

let rec range ?(step = 1) lo hi = if lo > hi then [] else lo :: range (lo + step) hi ~step
