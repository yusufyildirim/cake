open Query_Clause;
open Query_Statement;

let statement: update = { table: Table(None), where: Where([]) };
let empty =  Update(statement);
let where = (Update(st), expressions) => switch(st.where) {
| Where([]) => Update({ ...st, where: Where(expressions) });
| Where(prevExpressions) => Update({ ...st, where: Where(List.concat(expressions, prevExpressions)) });
};