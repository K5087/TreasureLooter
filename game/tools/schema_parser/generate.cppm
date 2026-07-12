module;
export module generate;
import common;
import std;

export{
    std::string generateClassCode(const ClassInfo& info);
    std::string generateSchemaCode(const SchemaInfo& schema_info);
}
