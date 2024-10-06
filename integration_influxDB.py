#Integração com o Código Python
#Certifique-se de que o código Python está configurado para enviar dados para o InfluxDB:

import requests
from influxdb import InfluxDBClient

# Configurações do InfluxDB
influxdb_host = 'localhost'
influxdb_port = 8086
influxdb_user = ''
influxdb_password = ''
influxdb_dbname = 'biofiltro'

# Inicializa o cliente do InfluxDB
client = InfluxDBClient(host=influxdb_host, port=influxdb_port, username=influxdb_user, password=influxdb_password, database=influxdb_dbname)

def write_data(methane_level):
    json_body = [
        {
            "measurement": "methane_levels",
            "tags": {
                "location": "biofilter"
            },
            "fields": {
                "methane": methane_level
            }
        }
    ]
    client.write_points(json_body)

# Exemplo de uso
methane_level = 1.23  # Este valor seria obtido do sensor
write_data(methane_level)