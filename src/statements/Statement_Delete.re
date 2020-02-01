open Query_Clause;
open Query_Statement;

let statement: delete = { from: From(None), where: Where([]) };
let empty =  Delete(statement);

let where = (Delete(st), expressions) => switch(st.where) {
| Where([]) => Delete({ ...st, where: Where(expressions) });
| Where(prevExpressions) => Delete({ ...st, where: Where(List.concat(expressions, prevExpressions)) });
};