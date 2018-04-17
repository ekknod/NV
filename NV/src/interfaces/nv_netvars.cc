#define _CRT_SECURE_NO_WARNINGS
#include "interfaces/nv_engine.h"
#include <vector>

namespace nv {
namespace windows {
    static void __SetValue(const char *v, char *b)
    {
        memset(b, 0, 260);
        strcat(b, v);
    }
    void EncryptedString(char *str, unsigned long val);
}
namespace netvars {
    
    struct recv_prop {
        char                *var_name;
        int                 recv_type;
        int                 flags;
        int                 string_buffer_size;
        bool                bInsideArray;
        const void          *extra_data;
        struct recv_prop    *array_prop;
        void                *array_length_proxy;
        void                *proxy_fn;
        void                *data_table_proxy_fn;
        struct recv_table   *data_table;
        int                 offset;
        int                 element_stride;
        int                 elements;
        const char          *parent_array_prop_name;
    };

    struct recv_table {
        struct recv_prop    *props;
        int                 props_count;
        void                *decoder;
        char                *name;
        bool                bInitialized;
        bool                bInMainList;
    };

    struct client_class {
        void                *create_fn;
        void                *create_event_fn;
        char                *network_name;
        struct recv_table   *recv_table;
        struct client_class *next;
        int                 id;
    };

    int netvar_team_num;
    int netvar_health;
    int netvar_life_state;
    int netvar_shots_fired;
    int netvar_vec_origin;
    int netvar_vec_view;
    int netvar_vec_punch;
    int netvar_studio_bone;

    static bool __dump_tables(std::vector<struct recv_table*> *tables)
    {
        struct client_class *c;

        tables->clear();
        c = (struct client_class*)engine::GetAllClasses();
        while( c ) {
            tables->push_back(c->recv_table);
            c = c->next;
        }
        return tables->empty() == false;
    }

    struct recv_table *__get_table(std::vector<struct recv_table*> tables, const char *name)
    {
        unsigned long     i;
        struct recv_table *table;

        for( i = 0; i < tables.size(); i++ ) {
            table = tables.at(i);
            if( table != 0 && _stricmp(table->name, name) == 0 ) {
                return table;
            }
        }
        return 0;
    }

    static int __get_prop(struct recv_table *table, const char *name)
    {
        int               offset, i, tmp;
        struct recv_prop  *recv_prop;
        struct recv_table *child;

        offset = 0;
        i = 0;
        for( i = 0; i < table->props_count; i++ ) {
            recv_prop = &table->props[i];
            child = recv_prop->data_table;

            if( child && (child->props_count > 0) ) {
                tmp = __get_prop(child, name);

                if( tmp ) {
                    offset += (recv_prop->offset + tmp);
                }
            }

            if( _stricmp(recv_prop->var_name, name) ) {
                continue;
            }
            return (recv_prop->offset + offset);
        }
        return offset;
    }

    static int __get_offset(std::vector<struct recv_table*> tables, const char *tableName, const char *propName)
    {
        struct recv_table *t;
        t = __get_table(tables, tableName);
        return t != 0 ? __get_prop(t, propName) : 0;
    }

    bool Init()
    {
        std::vector<struct recv_table*> tables;
        char                            table[260];
        char                            offset[260];

        if( !__dump_tables(&tables) ) {
            return false;
        }

        //
        // DT_BasePlayer
        //
        windows::__SetValue("DVVBeqaVlcpev", table);
        windows::EncryptedString(table, 0x64240920);
        {
            windows::__SetValue("m]`Hachrh", offset);
            windows::EncryptedString(offset, 0x64240920);
            netvar_health = __get_offset(tables, table, offset);
            if( netvar_health == 0 ) {
                return false;
            }

            windows::__SetValue("l]rlbPalvMborc|R1_", offset);
            windows::EncryptedString(offset, 0x98619421);
            netvar_vec_view = __get_offset(tables, table, offset);
            if( netvar_vec_view == 0 ) {
                return false;
            }

            windows::__SetValue("l]h`gc[}`va", offset);
            windows::EncryptedString(offset, 0x98619421);
            netvar_life_state = __get_offset(tables, table, offset);
            if( netvar_life_state == 0 ) {
                return false;
            }

            windows::__SetValue("l]Hfbgd", offset);
            windows::EncryptedString(offset, 0x98619421);
            netvar_vec_punch = __get_offset(tables, table, offset);
            if( netvar_vec_punch == 0 ) {
                return false;
            } else {
                netvar_vec_punch += 0x70;
            }
        }
        //
        // DT_BaseEntity
        //
        windows::__SetValue("EV[K`umLovm}x", table);
        windows::EncryptedString(table, 0x98619421);
        {
            windows::__SetValue("m]`TaciHuo", offset);
            windows::EncryptedString(offset, 0x64240920);
            netvar_team_num = __get_offset(tables, table, offset);
            if( netvar_team_num == 0 ) {
                return false;
            }

            windows::__SetValue("l]rlbIz`fkj", offset);
            windows::EncryptedString(offset, 0x98619421);
            netvar_vec_origin = __get_offset(tables, table, offset);
            if( netvar_vec_origin == 0 ) {
                return false;
            }
        }

        //
        // DT_CSPlayer
        //
        windows::__SetValue("EV[JRVdhxgv", table);
        windows::EncryptedString(table, 0x98619421);
        {
            windows::__SetValue("l]mZii|zGkvle", offset);
            windows::EncryptedString(offset, 0x98619421);
            netvar_shots_fired = __get_offset(tables, table, offset);
            if( netvar_shots_fired == 0 ) {
                return false;
            }
        }

        //
        // DT_BaseAnimating
        //
        windows::__SetValue("EV[K`umHokihuofn", table);
        windows::EncryptedString(table, 0x98619421);
        {
            windows::__SetValue("l]jOntklCmjl", offset);
            windows::EncryptedString(offset, 0x98619421);
            netvar_studio_bone = __get_offset(tables, table, offset);
            if( netvar_studio_bone == 0 ) {
                return false;
            } else {
                netvar_studio_bone += 0x1C;
            }
        }
        return true;
    }
}}
