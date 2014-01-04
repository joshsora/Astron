// Filename: Field.cpp
// Created by: drose (11 Oct, 2000)
//
// Copyright (c) Carnegie Mellon University.  All rights reserved.
//
// All use of this software is subject to the terms of the revised BSD
// license.  You should have received a copy of this license along
// with this source code in a file named "LICENSE."
//

#include "Field.h"
#include "File.h"
#include "StructType.h"
#include "HashGenerator.h"
namespace dclass   // open namespace
{

// constructor
Field::Field(Struct* strct, const std::string &name) :
	m_struct(strct), m_id(0), m_name(name), m_type(NULL), m_has_default_value(false)
{
}

// set_name sets the name of this field.  Returns false if a field with
//     the same name already exists in the containing struct.
bool Field::set_name(const std::string& name)
{
	// Check to make sure no other fields in our struct have this name
	if(m_struct->get_field_by_name(name) != (Field*)NULL)
	{
		return false;
	}

	m_name = name;
	return true;
}

// set_type sets the distributed type of the field and clear's the default value.
void Field::set_type(DistributedType* type)
{
	m_type = type;
	m_has_default_value = false;
	m_default_value.clear();
}

// set_default_value establishes a default value for this field.
//     Returns false if the value is invalid for the field.
bool Field::set_default_value(const std::string& default_value)
{
	// TODO: Validate default value
	m_has_default_value = true;
	m_default_value = default_value;
	return true;
}

// set_id sets the unique index number associated with the field.
void Field::set_id(unsigned int id)
{
	m_id = id;
}

// set_struct sets a pointer to the struct containing the field.
void Field::set_struct(StructType* strct)
{
	m_struct = strct;
}

// generate_hash accumulates the properties of this field into the hash.
void Field::generate_hash(HashGenerator& hashgen) const
{
	hashgen.add_int(m_id);
	hashgen.add_string(m_name);
	hashgen.add_string(m_default_value);
	m_type->generate_hash(hashgen);
	KeywordList::generate_hash(hashgen);
}


} // close namespace dclass
