#include <json-c/json.h>
#include <json-c/json_object.h>
#include <json-c/json_tokener.h>
#include <json-c/json_types.h>
#include <stdio.h>

struct dummy
{
    char *cmd;
};

void json2obj(char *str, json_object **obj)
{
    *obj = json_tokener_parse(str);
}

void json2data(char *str, struct dummy *messange_input_properties)
{
    struct json_object *obj;
    json2obj(str, &obj);

    messange_input_properties->cmd = (char *)json_object_get_string(json_object_object_get(obj, "cmd"));
}

int main()
{
    char *json_sample = "{\"cmd\": \"wkwk\"}";
    struct dummy dummy;
    dummy.cmd = "p";
    //json2data(json_sample, &dummy);

    printf("%s\n", (dummy.cmd == NULL) ? "true" : "false");
}