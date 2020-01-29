open Query_Clause;

type select = { columns, from, where, limit };
type insert = { table: string };
type update = { table: string, where: Query_Clause.where };
type delete = { table: string, where: Query_Clause.where };

type t = | Select(select) | Insert(insert) | Update(update) | Delete(delete);

module Select {
  let empty =  Select({ columns: `Columns([]), from: `From(None), where: `Where([]), limit: `Limit(None) });
}
