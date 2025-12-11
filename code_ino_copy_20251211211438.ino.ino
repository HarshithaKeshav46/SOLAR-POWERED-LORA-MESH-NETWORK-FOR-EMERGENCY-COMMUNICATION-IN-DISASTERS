
## GPS Tracker Firmware (click to expand)

<details>
  <summary>Show GPS tracker code (ESP8266)</summary>

<br>

```cpp

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// GPS Setup - Using SoftwareSerial
SoftwareSerial gpsSerial(D6, D5); // RX=D6, TX=D5
TinyGPSPlus gps;

// Web Server Setup
ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

// WiFi Access Point
const char* ssid = "GPS-Tracker";
const char* password = "12345678";

// Custom IP Configuration for NodeMCU
IPAddress local_ip(10, 0, 0, 1);      // NodeMCU IP address
IPAddress gateway(10, 0, 0, 1);       // Gateway IP
IPAddress subnet(255, 255, 255, 0);   // Subnet mask

// GPS Data Storage
float currentLat = 0;
float currentLon = 0;
float currentSpeed = 0;
int satellites = 0;

// Web Page HTML
const char* webpage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>GPS Tracker</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        body { 
            font-family: Arial; 
            background: #f0f0f0; 
            padding: 20px; 
            text-align: center;
        }
        .container { 
            max-width: 400px; 
            margin: 0 auto; 
            background: white; 
            padding: 20px; 
            border-radius: 10px; 
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
        }
        .data-box { 
            background: #e8f4f8; 
            padding: 15px; 
            margin: 10px 0; 
            border-radius: 5px; 
            text-align: left;
        }
        .label { 
            font-weight: bold; 
            color: #333; 
        }
        #map { 
            width: 100%; 
            height: 200px; 
            background: #e8f4f8; 
            border: 2px solid #ccc; 
            margin: 10px 0; 
            position: relative;
        }
        .marker { 
            position: absolute; 
            width: 20px; 
            height: 20px; 
            background: red; 
            border-radius: 50%; 
            border: 2px solid white;
            display: none;
        }
        .status { 
            padding: 10px; 
            margin: 10px 0; 
            border-radius: 5px; 
        }
        .connected { background: #d4edda; color: #155724; }
        .disconnected { background: #f8d7da; color: #721c24; }
    </style>
</head>
<body>
    <div class="container">
        <h1>📍 GPS Tracker</h1>
        
        <div class="status" id="status">Connecting...</div>
        
        <div class="data-box">
            <div class="label">Latitude:</div>
            <div id="latitude">0.000000</div>
        </div>
        
        <div class="data-box">
            <div class="label">Longitude:</div>
            <div id="longitude">0.000000</div>
        </div>
        
        <div class="data-box">
            <div class="label">Speed:</div>
            <div id="speed">0.0 km/h</div>
        </div>
        
        <div class="data-box">
            <div class="label">Satellites:</div>
            <div id="satellites">0</div>
        </div>
        
        <h3>Location Map</h3>
        <div id="map">
            <div class="marker" id="marker"></div>
        </div>
        
        <div style="margin-top: 20px; font-size: 12px; color: #666;">
            Connect to WiFi: <strong>GPS-Tracker</strong><br>
            Password: <strong>12345678</strong><br>
            Then visit: <strong>http://10.0.0.1</strong>
        </div>
    </div>

    <script>
        let socket;
        let marker = document.getElementById('marker');
        
        function connect() {
            socket = new WebSocket('ws://10.0.0.1:81');
            
            socket.onopen = function() {
                document.getElementById('status').className = 'status connected';
                document.getElementById('status').textContent = 'Connected - Waiting for GPS...';
            };
            
            socket.onmessage = function(event) {
                const data = JSON.parse(event.data);
                updateDisplay(data);
            };
            
            socket.onclose = function() {
                document.getElementById('status').className = 'status disconnected';
                document.getElementById('status').textContent = 'Disconnected - Retrying...';
                setTimeout(connect, 2000);
            };
        }
        
        function updateDisplay(data) {
            document.getElementById('latitude').textContent = data.lat.toFixed(6);
            document.getElementById('longitude').textContent = data.lon.toFixed(6);
            document.getElementById('speed').textContent = data.speed.toFixed(1) + ' km/h';
            document.getElementById('satellites').textContent = data.sats;
            
            if(data.lat !== 0) {
                marker.style.display = 'block';
                marker.style.left = '50%';
                marker.style.top = '50%';
                document.getElementById('status').textContent = 'GPS Active - Tracking';
            }
        }
        
        window.onload = connect;
    </script>
</body>
</html>
)rawliteral";

void setup() {

  
  Serial.begin(115200);
  
  // Start GPS SoftwareSerial
  gpsSerial.begin(9600);
  
  // Configure custom IP address for NodeMCU
  WiFi.softAPConfig(local_ip, gateway, subnet);
  
  // Create WiFi Access Point
  WiFi.softAP(ssid, password);
  
  Serial.println("WiFi Access Point Started!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
  
  // Serve web page
  server.on("/", []() {
    server.send(200, "text/html", webpage);
  });
  
  server.begin();
  
  // Start WebSocket
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  
  Serial.println("Web server started!");
  Serial.println("1. Connect to WiFi: GPS-Tracker");
  Serial.println("2. Open browser to: http://10.0.0.1");
  Serial.println("3. GPS connected to: RX=D6, TX=D5");
}

void loop() {
  server.handleClient();
  webSocket.loop();
  
  // Read GPS data from SoftwareSerial
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  // Check if GPS data updated
  if (gps.location.isUpdated()) {
    currentLat = gps.location.lat();
    currentLon = gps.location.lng();
    currentSpeed = gps.speed.kmph();
    satellites = gps.satellites.value();
    
    // Send data to all connected clients
    String jsonData = "{\"lat\":" + String(currentLat, 6) + 
                     ",\"lon\":" + String(currentLon, 6) + 
                     ",\"speed\":" + String(currentSpeed, 1) + 
                     ",\"sats\":" + String(satellites) + "}";
    
    webSocket.broadcastTXT(jsonData);
    
    Serial.print("Location: ");
    Serial.print(currentLat, 6);
    Serial.print(", ");
    Serial.print(currentLon, 6);
    Serial.print(" | Speed: ");
    Serial.print(currentSpeed);
    Serial.print(" km/h | Satellites: ");
    Serial.println(satellites);
  }
  
  delay(100);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_CONNECTED:
      Serial.printf("Client %u connected\n", num);
      // Send current data to new client
      if (currentLat != 0) {
        String jsonData = "{\"lat\":" + String(currentLat, 6) + 
                         ",\"lon\":" + String(currentLon, 6) + 
                         ",\"speed\":" + String(currentSpeed, 1) + 
                         ",\"sats\":" + String(satellites) + "}";
        webSocket.sendTXT(num, jsonData);
      }
      break;
  }
}
</br>
</details>```