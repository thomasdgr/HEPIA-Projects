extern crate gtfs;

use std::io::Write;
use std::fs::OpenOptions;

use gtfs::agency::*;
use gtfs::routes::*;
use gtfs::stop_times::*;
use gtfs::trips::*;
use gtfs::stops::*;
use gtfs::shapes::*;
use gtfs::validation;

/// Take a vector, a filename and the corresponding header to write in the file the content of the vector (generic function)
///
/// # Exemple
///
/// ```
///use gtfs::agency::*;
/// 
///let names = ["Transports Publics Genevois"];
///let agencies = Agency::read_agencies(&names, "./tpg_input/agency.txt".to_string()).unwrap();
/// 
///let header = "agency_id,agency_name,agency_url,agency_timezone,agency_lang,agency_phone";
///write_content(&agencies_vec, "./tpg_output/agency.txt", header);
/// ```
fn write_content<T>(v: &[T], path: &str, first_line: &str) where T: std::fmt::Display {
    let mut f = OpenOptions::new().write(true).append(true).create(true).open(path).expect("Unable to open file");
    writeln!(f, "{}", first_line).expect("Unable to write file");
    for item in v.iter(){
        writeln!(f, "{}", item).expect("Unable to write file");    
    }
}

fn create_gtfs(){
    let names = ["Transports Publics Genevois"];
    
    let agencies = Agency::read_agencies(&names, "./tpg_input/agency.txt".to_string()).unwrap();
    
    let mut stops = Stops::read_filtered_stops("./tpg_input/stops.txt".to_string()).unwrap();
    
    let mut routes = Routes::read_routes(&agencies, "./tpg_input/routes.txt".to_string()).unwrap();
    Routes::filter_routes(&mut routes);
    Routes::update_routes_trips(&mut routes, &Trips::read_filtered_trips("./tpg_input/trips.txt".to_string()).unwrap());
    Routes::update_routes_stoptimes(&mut routes, &Stoptimes::read_filtered_stop_times("./tpg_input/stop_times.txt".to_string()).unwrap());
    
    // keep only two "most common" trips for each route and their stoptimes
    let (trips, stop_times) = Trips::sort_trips(Trips::read_filtered_trips("./tpg_input/trips.txt".to_string()).unwrap(), &routes, &stops);    
    Routes::update_routes_trips(&mut routes, &trips);
    Routes::update_routes_stoptimes(&mut routes, &stop_times);
    
    // build the shapes from the routes
    let shapes = Shapes::build_shapes_and_update_routes(&mut routes, &mut stops).unwrap();    
    write_content(&shapes, "./tpg_output/shapes.txt", "shape_id,shape_pt_lat,shape_pt_lon,shape_pt_sequence");
}

fn validate(){
    let _ = validation::validate("22", "08", false, "./validation/22_tpg.png");

    let data = vec![
        2.1, 9.4, 14.0, 17.8, 19.4, 
        23.6, 26.9, 30.2, 31.0, 36.2, 
        41.8, 44.2, 42.8, 39.0, 38.1,
        37.3, 34.5, 36.6, 32.0, 30.8, 
        29.9, 25.7, 23.4, 22.0, 20.6, 
        17.2, 14.1, 12.2, 11.0, 8.6,
        5.7, 3.8, 2.2, 1.0, 0.3,
        ];
    let _ = validation::validate_from_array("22", "08", false, "./validation/22_abs.png", data);
}

fn main()  {
    create_gtfs();
    validate();
}