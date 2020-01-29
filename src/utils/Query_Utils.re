let joinWithSpace = (list: list(string)) => list |> String.concat(" ");
let joinWithAnd = (list: list(string)) => list |> String.concat(" AND ");
let joinWithOr = (list: list(string)) => list |> String.concat(" OR ");
let joinWithComma = (list: list(string)) => list |> String.concat(", ");
let quote = s => "\"" ++ s ++"\"";