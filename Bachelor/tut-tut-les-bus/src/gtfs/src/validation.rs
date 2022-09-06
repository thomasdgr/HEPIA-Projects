use std::fs::File;
use std::io::{prelude::*, BufReader};
use std::fmt;

use plotters::prelude::*;

use crate::stops::Stops;
use crate::stop_times::{Stoptimes};

#[derive(Debug, Clone)]
pub struct Transitload {
    pub route_id: String,
    pub direction_id: String,
    pub stop_id: String,
    pub stop_name: String,
    pub time: String,
    pub load: String,
    pub day_type: String,
    pub terminus_id: String
}

impl From<&Vec<String>> for Transitload {
    fn from(v: &Vec<String>) -> Self {
        Transitload { 
            route_id:v[0].to_owned(), 
            direction_id:v[1].to_owned(),
            stop_id:v[2].to_owned(),
            stop_name:v[3].to_owned(),
            time:v[4].to_owned(), 
            load:v[5].to_owned(),
            day_type:v[6].to_owned(),
            terminus_id:v[7].to_owned() }
    }
}

impl fmt::Display for Transitload {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "\"{}\",\"{}\",\"{}\",\"{}\",\"{}\",\"{}\",\"{}\",\"{}\"", 
            self.route_id, 
            self.direction_id, 
            self.stop_id,
            self.stop_name,
            self.time, 
            self.load,
            self.day_type,
            self.terminus_id)
    }
}

impl PartialEq for Transitload {
    fn eq(&self, other: &Transitload) -> bool {
        self.route_id.eq(&other.route_id) && 
        self.direction_id.eq(&other.direction_id) &&
        self.stop_id.eq(&other.stop_id) &&
        self.stop_name.eq(&other.stop_name) &&
        self.time.eq(&other.time) &&
        self.load.eq(&other.load) &&
        self.day_type.eq(&other.day_type) &&
        self.terminus_id.eq(&other.terminus_id) 
    }
}

impl Transitload {
    // create a vector of Transit_load from a file
    pub fn read_transit_loads(path: String) -> Option<Vec<Transitload>> {
        let mut reader = BufReader::new(File::open(path).ok()?);
        let _ = reader.read_line(&mut String::new());
        let mut transit_loads = reader.lines()
            .into_iter()
            .map(|line| {
                let v = line.unwrap()
                    .split(',')
                    .map(|word| word.replace('\"', ""))
                    .collect::<Vec<_>>();
                    Transitload::from(&vec![v[5].to_owned(), 
                        v[6].to_owned(), 
                        0.to_string(), 
                        v[2].to_owned(), 
                        v[3].to_owned(), 
                        format!("{}.{}",v[7], v[8]), 
                        v[4].to_owned(), 
                        v[9].to_owned()])
            })
            .collect::<Vec<_>>();
            transit_loads = Transitload::filter_transit_loads(transit_loads);
            Transitload::sort_transit_loads(&mut transit_loads);
            transit_loads = Transitload::match_stop_name(transit_loads,
                 Stops::read_filtered_stops("./tpg_input/stops.txt".to_string()).unwrap());

        Some(transit_loads)
    }

    pub fn filter_transit_loads(transit_loads: Vec<Transitload>) -> Vec<Transitload> {
        transit_loads.iter()
            .filter(|s| 
                s.day_type.contains("NORMAL") && 
                matches!(s.time.parse::<i32>().unwrap(), 6..=20))
            .map(|s| s.to_owned())
            .collect::<Vec<_>>()
    }

    pub fn sort_transit_loads(transit_loads: &mut [Transitload])  {
        transit_loads.sort_by(|a, b| a.direction_id.cmp(&b.direction_id));
        transit_loads.sort_by(|a, b| a.time.cmp(&b.time));
        transit_loads.sort_by(|a, b| a.terminus_id.cmp(&b.terminus_id));
        transit_loads.sort_by(|a, b| a.route_id.cmp(&b.route_id));
    }

    pub fn match_stop_name(transit_loads: Vec<Transitload>, stops: Vec<Stops>) -> Vec<Transitload> {
        let mut new_transit_loads: Vec<Transitload> = Vec::new();
        for item in transit_loads.iter() {
            for stop in stops.iter() {
                if item.stop_name == stop.stop_name {
                    new_transit_loads.push(Transitload::from(&vec![item.route_id.to_owned(), item.direction_id.to_owned(), stop.stop_id.to_owned(), item.stop_name.to_owned(), item.time.to_owned(), item.load.to_owned(), item.day_type.to_owned(), item.terminus_id.to_owned()]));
                    break;
                }
            }
        }
        new_transit_loads
    }

    pub fn sort_by_stop_times(transit_loads: &mut [Transitload], stoptimes: Vec<Stoptimes>, route_id: &str, time: &str) -> Vec<Transitload> {
        let mut new_transit_loads: Vec<Transitload> = Vec::new();
        for item in transit_loads.iter() {
            if item.route_id == route_id && item.time == time {
                new_transit_loads.push(item.to_owned());
            }
        }
        let mut new_stoptimes: Vec<Stoptimes> = Vec::new();
        for s in stoptimes.iter() {
            if s.trip_id.contains(&format!("-{}-",route_id)[..]) {
                new_stoptimes.push(s.to_owned());
            }
        }
        let mut new_transit_loads_sorted: Vec<Transitload> = Vec::new();
        for i in new_stoptimes.into_iter() {
            for j in 0..new_transit_loads.len() {
                if i.stop_id == new_transit_loads[j].stop_id {
                    new_transit_loads_sorted.push(new_transit_loads[j].to_owned());                                        
                    new_transit_loads.remove(j);
                    break;
                }
            }
        }
        new_transit_loads_sorted.sort_by(|a, b| a.direction_id.cmp(&b.direction_id));
        new_transit_loads_sorted
    }
}


pub fn create_vec_from_transit_loads(transit_loads: Vec<Transitload>, going: bool) -> Vec<(u32,f32)> {
    let mut vec: Vec<(u32,f32)> = Vec::new();
    let mut count = 0;
    for item in transit_loads.iter() {
        if going {
            if item.direction_id.contains("Aller") {
                vec.push((count, item.load.parse::<f32>().unwrap()));
                count += 1;
            }
        } else if item.direction_id.contains("Retour") {
            vec.push((count, item.load.parse::<f32>().unwrap()));
            count += 1;
        }
    }
    vec
}

pub fn get_max_users(transit_loads: Vec<Transitload>) -> f32 {
    let mut max_users: f32 = 0.0;
    for item in transit_loads.iter() {
        if item.load.parse::<f32>().unwrap() > max_users {
            max_users = item.load.parse::<f32>().unwrap();
        }
    }
    max_users
}

pub fn update_loads(vec: &mut Vec<(u32, f32)>, data: Vec<f32>)  {
    for i in 0..vec.len() {
        vec[i] = (vec[i].0, data[i]);
    }
}

pub fn draw_plot(transit_loads: &mut [Transitload], going: bool, filename: &str, vec: Vec<(u32, f32)>) -> Result<(), Box<dyn std::error::Error>>{
    let root = BitMapBackend::new(filename, (640, 480)).into_drawing_area();
    root.fill(&WHITE)?;

    let tmp = transit_loads.iter().next().unwrap();
    let max_users = get_max_users(transit_loads.to_vec());
    
    println!("nb arrêts: {}", transit_loads.iter()
        .filter(|s| {
            if going { 
                s.direction_id.contains("Aller") 
            } else { 
                s.direction_id.contains("Retour")
            }
        })
        .map(|s| println!("{}", s)).count());    

    let mut chart = ChartBuilder::on(&root)
        .x_label_area_size(50)
        .y_label_area_size(50)
        .margin(5)
        .caption(
            format!("Charge moyenne de la ligne {} (dir. {}) à {}:00", 
                tmp.route_id, 
                tmp.terminus_id, 
                tmp.time), 
            ("sans-serif", 20.0))
        .build_cartesian_2d(
            (0u32..vec.len() as u32).into_segmented(),
            0f32..max_users)?;

    chart
        .configure_mesh()
        .disable_x_mesh()
        .bold_line_style(&WHITE.mix(0.3))
        .y_desc("Nb. Personnes")
        .x_desc("Indices des Arrêts")
        .axis_desc_style(("sans-serif", 15))
        .draw()?;

    chart.draw_series(
        Histogram::vertical(&chart)
            .style(RED.mix(0.8).filled())
            .data(vec),
    )?;

    Ok(())
}

pub fn validate(route_id: &str, time: &str, going: bool, filename: &str)  {
    let transit_loads = &mut Transitload::sort_by_stop_times(
        &mut Transitload::read_transit_loads("./tpg_input/tpg_load/Charge Réseau TPG - Septembre - Novembre 2021.csv".to_string()).unwrap(),
        Stoptimes::read_filtered_stop_times("./tpg_input/stop_times.txt".to_string()).unwrap(),
            route_id,
            time);
    let vec = create_vec_from_transit_loads(transit_loads.to_vec(), going);

    let _ = draw_plot(transit_loads, going, filename, vec);
}

pub fn validate_from_array(route_id: &str, time: &str, going: bool, filename: &str, data: Vec<f32>)  {
    let mut transit_loads = Transitload::sort_by_stop_times(
        &mut Transitload::read_transit_loads("./tpg_input/tpg_load/Charge Réseau TPG - Septembre - Novembre 2021.csv".to_string()).unwrap(),
        Stoptimes::read_filtered_stop_times("./tpg_input/stop_times.txt".to_string()).unwrap(),
            route_id,
            time);
    let mut vec = create_vec_from_transit_loads(transit_loads.to_vec(), going);
    if vec.len() == data.len() {
        update_loads(&mut vec, data);    
    } else {
        panic!("Erreur: wrong size: {} in data, should be {}", data.len(), vec.len());
    }
    let _ = draw_plot(&mut transit_loads, going, filename, vec);
}