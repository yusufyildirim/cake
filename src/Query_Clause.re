// TODO: I'm not sure about this. There has to be a better way to manage these types. Using polyvariants is kinda pointless right now.
type columns = [ `Columns(list(string)) ];
type from = [ `From(option(string)) ];
type where = [ `Where(list(Query_Expression.t)) ];
type limit = [ `Limit(option(int)) ];