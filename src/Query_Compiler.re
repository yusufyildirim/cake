open Query_Expression;
module QU = Query_Utils;

let compileValue = fun
| Int(v) => string_of_int(v)
| String(v) => QU.quote(v)
| Bool(v) => string_of_bool(v)

let compileOperator = fun
| Eq(value) => "=" ++ compileValue(value)
| NotEq(value) => "<> " ++ compileValue(value)
| GreaterThan(value) => "> " ++ compileValue(value)
| LessThan(value) => "< " ++ compileValue(value)
| GreaterThanOrEqual(value) => ">= " ++ compileValue(value)
| LessThanOrEqual(value) => "<= " ++ compileValue(value)
| Between(value1, value2) => "BETWEEN " ++ QU.joinWithAnd([compileValue(value1), compileValue(value2)])
| Like(value) => "LIKE " ++ compileValue(value)
| In(_values) => "IN :TODO";

let columns = fun
| `Columns([]) => "*"
| `Columns(columns) => List.map(columns, QU.quote) -> QU.joinWithComma;

let from = fun
| `From(None) => ""
| `From(Some(table)) => ["FROM", table] -> QU.joinWithSpace;

let where = fun
| `Where([]) => ""
| `Where(expressions) =>  {
  [
    "WHERE",
    expressions
    -> List.map(fun
        | Single(column, op) => [column, compileOperator(op)] -> QU.joinWithSpace
        | Compose(_expr1, _composeOp, _expr2) => ":TODO"
      )
    -> QU.joinWithAnd
  ] -> QU.joinWithSpace;
};

let limit = fun
| `Limit(None) => ""
| `Limit(Some(number)) => ["LIMIT", string_of_int(number)] -> QU.joinWithSpace;


let select = (statement: Query_Statement.select) =>
  [
    "SELECT",
    columns(statement.columns),
    from(statement.from),
    where(statement.where),
    limit(statement.limit),
  ] -> QU.joinWithSpace;

let insert = (_statement) => {
  ""
}

let update = (_statement) => {
  ""
}

let delete = (_statement) => {
  ""
}

let compile = (statement: Query_Statement.t) => {
  switch statement {
  | Select(st) => select(st)
  | Insert(st) => insert(st)
  | Update(st) => update(st)
  | Delete(st) => delete(st)
  };
}