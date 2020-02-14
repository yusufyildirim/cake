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

let orderDirectionToString = fun
| Asc => "ASC"
| Desc => "DESC";

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
| Columns(columns) => columns -> QU.joinWithComma;

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

let limit = fun
| Limit(None) => ""
| Limit(Some(number)) => ["LIMIT", string_of_int(number)] -> QU.joinWithSpace;

let groupBy = fun
| GroupBy([]) => ""
| GroupBy(list) => ["GROUP BY", QU.joinWithComma(list)] -> QU.joinWithSpace;

let orderBy = fun
| OrderBy([]) => ""
| OrderBy(list) => "ORDER BY " ++ (List.map(list, ((col, direction)) => col ++ " " ++ orderDirectionToString(direction)) -> QU.joinWithComma);

// INSERT
let into = fun
| Into(None) => ""
| Into(Some(table)) => ["INTO", table] -> QU.joinWithSpace;

let row = list => List.map(list, valueToString) -> QU.joinWithComma -> QU.wrapWithParantheses;

let values = fun
| Values([]) => ""
| Values(list) => ["VALUES", List.map(list, row) -> QU.joinWithComma] -> QU.joinWithSpace;

let select = (statement: Query_Statement.select) =>
  [
    "SELECT",
    columns(statement.columns),
    from(statement.from),
    where(statement.where),
    limit(statement.limit),
    groupBy(statement.groupBy),
    orderBy(statement.orderBy),
  ]
  -> QU.joinWithSpace;

let insert = (statement: Query_Statement.insert) =>
  [
    "INSERT",
    into(statement.into),
    columns(statement.columns) -> QU.wrapWithParantheses,
    values(statement.values),
  ]
  -> QU.joinWithSpace;

/*let update = (_statement) => "";

let delete = (_statement) => "";*/

let toSQL: type v. Query_Statement.t(v) => string = (statement) => {
  open Query_Statement;

  switch statement {
  | Select(st) => select(st)
  | Insert(st) => insert(st)
  | Update(_st) => "" //update(st)
  | Delete(_st) => "" //delete(st)
  };
}