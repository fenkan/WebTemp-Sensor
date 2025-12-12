using System.Net.Http;
using System.Net.Http.Json;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Http;

var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

// NodeMCU IP
string nodeMcuUrl = "http://192.168.0.7/";

// Globala värden för max/min
double? maxTemp = null;
double? minTemp = null;

app.UseHttpsRedirection();
app.UseDefaultFiles(); // letar efter index.html
app.UseStaticFiles();

//Endpoint för sensor data
app.MapGet("/sensor", async () => 
{
using var client = new HttpClient();
    var data = await client.GetFromJsonAsync<SensorData>(nodeMcuUrl);

    if (data != null)
    {
        // Uppdatera max och min
        if (maxTemp == null || data.Temperature > maxTemp) maxTemp = data.Temperature;
        if (minTemp == null || data.Temperature < minTemp) minTemp = data.Temperature;

        // Data som javascript hämtar
        return Results.Json(new
        {
            temperature = data.Temperature,
            humidity = data.Humidity,
            maxTemp,
            minTemp
        });
    }

    return Results.Json(new { error = "NodeMCU unreachable" });
});  

app.Run();

public class SensorData
{
    public double Temperature { get; set; }
    public double Humidity { get; set; }
}