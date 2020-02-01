module Builder = {
  module Select = Statement_Select;
  module Insert = Statement_Insert;
  module Update = Statement_Update;
  module Delete = Statement_Delete;

  include Expression_Builder;
};
module Compiler = Query_Compiler;