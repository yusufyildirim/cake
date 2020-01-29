open Query_Clause;

type select = { columns, from, where, limit };
type insert = { table: string };
type update = { table: string, where: Query_Clause.where };
type delete = { table: string, where: Query_Clause.where };

type t = | Select(select) | Insert(insert) | Update(update) | Delete(delete);

module Select {
  let statement = { columns: `Columns([]), from: `From(None), where: `Where([]), limit: `Limit(None) };
  let empty =  Select(statement);
}

module Insert {
  let statement = { table: "" };
  let empty =  Insert(statement);
}

module Update {
  let statement: update = { table: "", where: `Where([]) };
  let empty =  Update(statement);
}

module Delete {
  let statement: delete = { table: "", where: `Where([]) };
  let empty =  Delete(statement);
}
