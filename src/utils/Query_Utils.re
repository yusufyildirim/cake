let keepNonEmpty = List.keep(_, i => i != "");
let joinWithSpace = (list: list(string)) => list -> keepNonEmpty |> String.concat(" ");
let joinWithAnd = (list: list(string)) => list -> keepNonEmpty |> String.concat(" AND ");
let joinWithOr = (list: list(string)) => list -> keepNonEmpty |> String.concat(" OR ");
let joinWithComma = (list: list(string)) => list -> keepNonEmpty |> String.concat(", ");
let quote = s => "\"" ++ s ++"\"";
let wrapWithParantheses = s => "(" ++ s ++")";