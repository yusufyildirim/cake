open Query_Expression;
open Query_Clause;
module QU = Query_Utils;

type statement('a) = Query_Statement.t('a);
type expression = Query_Expression.t;

let valueToString = fun
| Int(v) => string_of_int(v)
| Float(v) => Js.Float.toString(v)
| String(v) => QU.quote(v)
| Bool(v) => string_of_bool(v)
| Null => "NULL";

let operator = fun
| Eq(col, value) => col ++ " = " ++ valueToString(value)
| NotEq(col, value) => col ++ " <> " ++ valueToString(value)
| GreaterThan(col, value) => col ++ " > " ++ valueToString(value)
| LessThan(col, value) => col ++ " < " ++ valueToString(value)
| GreaterThanOrEqual(col, value) => col ++ " >= " ++ valueToString(value)
| LessThanOrEqual(col, value) => col ++ " <= " ++ valueToString(value)
| Between(col, value1, value2) => col ++ " BETWEEN " ++ QU.joinWithAnd([valueToString(value1), valueToString(value2)])
| Like(col, value) => col ++ " LIKE " ++ valueToString(value)
| In(col, _values) => col ++ "IN :TODO";


let rec expression = fun
| Single(op) => operator(op)
| And(ops) => "AND (" ++ List.map(ops, expression) -> QU.joinWithSpace ++ ")" 
| Or(ops)  => "OR (" ++ List.map(ops, expression) -> QU.joinWithSpace ++ ")";

let columns = fun
| Columns([]) => "*"
| Columns(columns) => List.map(columns, QU.quote) -> QU.joinWithComma;

let from = fun
| From(None) => ""
| From(Some(table)) => ["FROM", table] -> QU.joinWithSpace;

let where = fun
| Where([]) => "" 
| Where(expressions) =>  {
  [
    "WHERE",
    expressions -> List.map(expression) -> QU.joinWithSpace
  ] -> QU.joinWithSpace;
};

let select = (statement: Query_Statement.select) =>
  [
    "SELECT",
    columns(statement.columns),
    from(statement.from),
    where(statement.where),
    // limit(statement.limit),
  ] -> QU.joinWithSpace;

let insert = (_statement) => "";

let update = (_statement) => "";

let delete = (_statement) => "";

let toSQL: type v. Query_Statement.t(v) => string = (statement) => {
  open Query_Statement;

  switch statement {
  | Select(st) => select(st)
  | Insert(st) => insert(st)
  | Update(st) => update(st)
  | Delete(st) => delete(st)
  };
}

/*
open Query_Expression;
module QU = Query_Utils;

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
*/
/*
let compile = (statement: Query_Statement.t) => {
  switch statement {
  | Select(st) => select(st)
  | Insert(st) => insert(st)
  | Update(st) => update(st)
  | Delete(st) => delete(st)
  };
}*/