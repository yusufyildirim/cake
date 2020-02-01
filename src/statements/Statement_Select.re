open Query_Clause;
open Query_Statement;

let statement = { columns: Columns([]), from: From(None), where: Where([]), limit: Limit(None) };
let empty =  Select(statement);
let from = (table) => Select({...statement, from: From(Some(table)) });
let where = (Select(st), expressions) => switch(st.where) {
| Where([]) => Select({ ...st, where: Where(expressions) });
| Where(prevExpressions) => Select({ ...st, where: Where(List.concat(expressions, prevExpressions)) });
};
let columns = (Select(st), columns) => Select({ ...st, columns: Columns(columns) });
let limit = (Select(st), num) => Select({ ...st, limit: Limit(Some(num)) });