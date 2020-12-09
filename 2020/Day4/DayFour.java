import java.util.*;
import java.io.*;

public class DayFour {
    public static class Passport {
        Map<String, String> fields = new HashMap<>();

        public Passport() {
            fields.put("byr", "");
            fields.put("iyr", "");
            fields.put("eyr", "");
            fields.put("hgt", "");
            fields.put("hcl", "");
            fields.put("ecl", "");
            fields.put("pid", "");
            fields.put("cid", "");
        }

        public void setField(String key, String value) {
            fields.put(key, value);
        }

        private boolean checkByr() {
            try {
                int val = Integer.parseInt(fields.get("byr"));
                return (val >= 1920) && (val <= 2002);
            } catch (Exception err) {
                return false;
            }
        }

        private boolean checkIyr() {
            try {
                int val = Integer.parseInt(fields.get("iyr"));
                return (val >= 2010) && (val <= 2020);
            } catch (Exception err) {
                return false;
            }
        }

        private boolean checkEyr() {
            try {
                int val = Integer.parseInt(fields.get("eyr"));
                return (val >= 2020) && (val <= 2030);
            } catch (Exception err) {
                return false;
            }
        }

        private boolean checkHgt() {
            try {
                String value = fields.get("hgt");
                String suffix = value.substring(value.length() - 2);
                if (!(suffix.equals("cm") || suffix.equals("in"))) {
                    return false;
                }
                if (suffix.equals("cm")) {
                    int val = Integer.parseInt(value.substring(0, value.length() - 2));
                    return (val >= 150) && (val <= 193);
                }
                if (suffix.equals("in")) {
                    int val = Integer.parseInt(value.substring(0, value.length() - 2));
                    return (val >= 59) && (val <= 76);
                }
                return false;
            } catch (Exception err) {
                return false;
            }
        }

        private boolean checkHcl() {
            String value = fields.get("hcl");
            if (value.length() != 7) {
                return false;
            }
            for (int i = 0; i < value.length(); i++) {
                if (i == 0 && value.charAt(i) != '#') {
                    return false;
                }
                if (i != 0) {
                    int curr = value.charAt(i) - '0';
                    if (curr < 0 || curr > 9) {
                        int curr2 = value.charAt(i) - 'a';
                        if (curr2 < 0 || curr2 > 6) {
                            return false;
                        }
                    }
                }
            }
            return true;
        }

        private boolean checkEcl() {
            String value = fields.get("ecl");
            return value.equals("amb") || value.equals("blu") || value.equals("brn")
                    || value.equals("gry") || value.equals("grn") || value.equals("hzl")
                    || value.equals("oth");
        }

        private boolean checkPid() {
            String value = fields.get("pid");
            if (value.length() != 9) {
                return false;
            }
            Integer val = Integer.parseInt(value);
            return (val >= 0) && (val <= 999999999);
        }

        public boolean checkValidPartOne() {
            return !fields.get("byr").equals("") && !fields.get("iyr").equals("")
                    && !fields.get("eyr").equals("") && !fields.get("hgt").equals("")
                    && !fields.get("hcl").equals("") && !fields.get("ecl").equals("")
                    && !fields.get("pid").equals("");
        }

        public boolean checkValidPartTwo() {
            return checkByr() && checkIyr() && checkEyr() && checkHgt()
                    && checkHcl() && checkEcl() && checkPid();
        }
    }

    public static int partOne() throws IOException {
        File input = new File("./input4.txt");
        Scanner sc = new Scanner(input);
        String line = "";
        int countValid = 0;
        while (sc.hasNextLine()) {
            Passport passport = new Passport();
            while (sc.hasNextLine() && !(line = sc.nextLine()).equals("")) {
                String[] parse = line.trim().split(" ");
                for (int i = 0; i < parse.length; i++) {
                    String[] keyValue = parse[i].split(":");
                    String key = keyValue[0];
                    String value = keyValue[1];
                    passport.setField(key, value);
                }
            }
            if (passport.checkValidPartOne()) {
                countValid++;
            }
        }
        return countValid;
    }

    public static long partTwo() throws IOException {
        File input = new File("./input4.txt");
        Scanner sc = new Scanner(input);
        String line = "";
        int countValid = 0;
        while (sc.hasNextLine()) {
            Passport passport = new Passport();
            while (sc.hasNextLine() && !(line = sc.nextLine()).equals("")) {
                String[] parse = line.trim().split(" ");
                for (int i = 0; i < parse.length; i++) {
                    String[] keyValue = parse[i].split(":");
                    String key = keyValue[0];
                    String value = keyValue[1];
                    passport.setField(key, value);
                }
            }
            if (passport.checkValidPartTwo()) {
                countValid++;
            }
        }
        return countValid;
    }

    public static void main(String[] args) {
        try {
            System.out.println(partOne());
            System.out.println(partTwo());
        } catch (IOException err) {
            System.out.println(err);
        }
    }
}