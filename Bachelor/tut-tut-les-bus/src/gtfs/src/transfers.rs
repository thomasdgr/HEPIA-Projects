use std::fs::File;
use std::io::{prelude::*, BufReader};
use std::fmt;

use crate::stop_times::{Stoptimes};

#[derive(Debug)]
pub struct Transfers {
    pub from_stop_id: String,
    pub to_stop_id: String,
    pub transfer_type: String,
    pub min_transfer_time: String
}

impl From<&Vec<String>> for Transfers {
    fn from(v: &Vec<String>) -> Self {
        Transfers { from_stop_id:v[0].to_owned(),
            to_stop_id:v[1].to_owned(),
            transfer_type:v[2].to_owned(),
            min_transfer_time:v[3].to_owned() }
    }
}

impl fmt::Display for Transfers {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "\"{}\",\"{}\",\"{}\",\"{}\"", 
            self.from_stop_id, 
            self.to_stop_id, 
            self.transfer_type, 
            self.min_transfer_time)
    }
}

impl PartialEq for Transfers {
    fn eq(&self, other: &Transfers) -> bool {
        self.from_stop_id.eq(&other.from_stop_id) && 
        self.to_stop_id.eq(&other.to_stop_id) &&
        self.transfer_type.eq(&other.transfer_type) &&
        self.min_transfer_time.eq(&other.min_transfer_time)
    }
}

impl Transfers {
    /// Return an option on a vector of Transfers created from a file and a vector of Stoptimes
    ///
    /// # Exemple
    ///
    /// ```
    ///use gtfs::Transfers::*;
    /// 
    ///let stops = Transfers::read_transfers(&stop_times_vec, "./tpg_input/transfers.txt".to_string()).unwrap();
    ///
    ///let header = "from_stop_id,to_stop_id,transfer_type,min_transfer_time";
    ///write_content(&stops, "./tpg_output/transfers.txt", header);
    /// ```
    pub fn read_transfers(stop_times: &[Stoptimes], path: String) -> Option<Vec<Transfers>> {
        let reader = BufReader::new(File::open(path).ok()?);
        let mut transfers = reader.lines()
            .into_iter()
            .flat_map(|line| {
                let v = line.unwrap()
                    .split(',')
                    .map(|word| word.replace('\"', ""))
                    .collect::<Vec<_>>();
                stop_times.iter()
                    .filter(|s| (v[0] == s.stop_id || v[1] == s.stop_id))
                    .map(|_stop_id| Transfers::from(&v))
                    .collect::<Vec<_>>()})
        .collect::<Vec<_>>();
        transfers.dedup();
        Some(transfers)    
    }    
}