open Query_Clause;

type select = {
  columns: t(columns),
  from: t(from),
  where: t(where),
  limit: t(limit),
  orderBy: t(orderBy),
  groupBy: t(groupBy),
};
type insert = { into: t(into) };
type update = { table: t(table), where: t(where) };
type delete = { from: t(from), where: t(where) };

type t('a) = 
| Select(select): t(select)
| Insert(insert): t(insert)
| Update(update): t(update)
| Delete(delete): t(delete);