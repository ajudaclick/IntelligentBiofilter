import requests
from influxdb import InfluxDBClient

# Configurações do InfluxDB
influxdb_host = 'your_influxdb_host'
influxdb_port = 8086
influxdb_user = 'your_username'
influxdb_password = 'your_password'
influxdb_dbname = 'your_database'

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