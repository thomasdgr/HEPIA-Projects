use std::fs::File;
use std::io::{prelude::*, BufReader};
use std::fmt;

#[derive(Debug, PartialEq)]
pub struct Kml {
    pub stop_name: String,
    pub stop_lat: String,
    pub stop_lon: String,
    pub routes: String
}

impl From<&Vec<String>> for Kml {
    fn from(v: &Vec<String>) -> Self {
        Kml { 
            stop_name:v[0].to_owned(),
            stop_lat:v[1].to_owned(),
            stop_lon:v[2].to_owned(),
            routes:v[3].to_owned() }
    }
}

impl fmt::Display for Kml {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "\"{}\",{},{},\"{}\"", 
            self.stop_name, 
            self.stop_lat, 
            self.stop_lon, 
            self.routes)
    }
}

impl Kml {
    // create a vector of Kml from a file
    /// Return an option on a vector of Kml created from a file
    ///
    /// # Exemple
    ///
    /// ```
    ///use gtfs::Kml::*;
    /// 
    ///let kml = Kml::read_kml("./tpg_input/kml_data/data_read_from_kml.txt".to_string()).unwrap();
    /// ```
    pub fn read_kml(path: String) -> Option<Vec<Kml>> {
        let mut reader = BufReader::new(File::open(path).ok()?);
        let _ = reader.read_line(&mut String::new());
        let kml = reader.lines()
            .map(|line| {
                let v = line.unwrap()
                    .split("\",")
                    .map(|word| word.replace('\"', ""))
                    .collect::<Vec<_>>();
                let coords = v.get(2)
                    .unwrap()
                    .split(',')
                    .map(|word| word.replace(' ', ""))
                    .collect::<Vec<_>>();
                Kml::from(&vec![v[0].to_owned(), coords[1].to_owned(), coords[0].to_owned(), v[1].to_owned()])
            })
            .collect::<Vec<_>>();
        Some(kml)
    }
}