import numpy as np
from typing import Tuple
METADATA_SIZE = 6


def _parse_metadata(metadata: bytes) -> Tuple[type, int]:
    """
    Parse the metadata for a vec file.

    Parameters:
    metadata (bytes): The metadata bytes

    Returns:
    (type, int): The type and the number of component of the vector
    """

    little_endian = bool(metadata[0])
    endianness = 'little' if little_endian else 'big'

    size_of_components = int(metadata[1])
    # For now we only consider two types
    datatype = np.float64 if size_of_components == 8 else np.float

    # Recover our 32 bit integer specifying the endianness
    nb_components = int.from_bytes(metadata[2:], endianness)

    return datatype, nb_components


def load_vector(filename: str) -> np.ndarray:
    """
    Load a vector from a file.

    Parameters:
    filename (str): The name of the file containing the vector

    Returns:
    np.ndarray: The vector

    """
    file = open(filename, 'rb')
    # Read our metadata struct
    metadata = file.read(METADATA_SIZE)

    datatype, nb_components = _parse_metadata(metadata)

    array = np.fromfile(file, dtype=datatype, count=nb_components)

    file.close()
    return array
