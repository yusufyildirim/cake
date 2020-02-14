open Query_Clause;
open Query_Statement;

let statement = { into: Into(None), columns: Columns([]), values: Values([]) };
let empty =  Insert(statement);
let into = (table) => Insert({ ...statement, into: Into(Some(table)) });
let columns = (Insert(st), columns) => Insert({ ...st, columns: Columns(columns) });
let values = (Insert(st), valueList) => Insert({ ...st, values: Values(valueList) })