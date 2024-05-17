import folium 
import os 
 
#create a map 
m = folium.Map(location = [30.065404011 , 31.2788650] , zoom_start = 17) 
walk_data = os.path.join('data.json') #"credit" name of files which contains the coordinates 
folium.GeoJson(walk_data, name = 'walk').add_to(m) 
points = m.get_bounds() 
 
#Add marker 
#Start Point 
folium.Marker(location = points[0] , popup = "<strong>Start_Point</strong>" , tooltip = "Click for more information" , icon = folium.Icon(color = "red") ).add_to(m) 
#End Point 
folium.Marker(location = points[-1] , popup = "<strong>End_Point</strong>" , tooltip = "Click for more information" , icon = folium.Icon(color = "blue") ).add_to(m) 
 
m.save("project.html")
