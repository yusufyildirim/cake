open Query_Clause;
open Query_Statement;

let statement = { into: Into(None) };
let empty =  Insert(statement);
let into = (table) => Insert({ ...statement, into: Into(Some(table)) });